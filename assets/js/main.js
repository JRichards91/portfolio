document.addEventListener('DOMContentLoaded', () => {
  /* ------------ Baseurl for fetches ------------ */
  const baseurl = document.documentElement.getAttribute('data-baseurl') || '';

  /* ------------ Burger -> Popover Drawer ------------ */
  const burger   = document.querySelector('.burger');
  const drawer   = document.getElementById('mobile-drawer');
  const backdrop = document.querySelector('.drawer-backdrop');

  function positionPopover() {
    if (!burger || !drawer) return;
    const r = burger.getBoundingClientRect();
    const top = r.bottom + window.scrollY + 8;
    const right = Math.max(8, window.innerWidth - r.right + 8);
    drawer.style.setProperty('--dd-top', `${top}px`);
    drawer.style.setProperty('--dd-right', `${right}px`);
  }

  const showBackdrop = () => {
    if (!backdrop) return;
    backdrop.hidden = false;
    // force reflow to enable transition from 0 opacity
    // eslint-disable-next-line no-unused-expressions
    backdrop.offsetHeight;
    backdrop.classList.add('is-visible');
  };
  const hideBackdrop = () => { if (backdrop) backdrop.classList.remove('is-visible'); };

  function openDrawer() {
    if (!burger || !drawer) return;
    positionPopover();
    burger.setAttribute('aria-expanded', 'true');
    drawer.classList.add('is-open');
    drawer.setAttribute('aria-hidden', 'false');
    showBackdrop();
    trapFocus(drawer);
  }
  function closeDrawer() {
    if (!burger || !drawer) return;
    burger.setAttribute('aria-expanded', 'false');
    drawer.classList.remove('is-open');
    drawer.setAttribute('aria-hidden', 'true');
    hideBackdrop();
    releaseFocus();
    burger.focus();
  }

  // Backdrop lifecycle
  if (backdrop) {
    backdrop.addEventListener('transitionend', () => {
      if (!backdrop.classList.contains('is-visible')) backdrop.hidden = true;
    });
    backdrop.addEventListener('click', closeDrawer);
  }

  if (burger) {
    burger.addEventListener('click', () => {
      const expanded = burger.getAttribute('aria-expanded') === 'true';
      expanded ? closeDrawer() : openDrawer();
    });
  }

  // Close on ESC; close when clicking a link inside
  document.addEventListener('keydown', (e) => { if (e.key === 'Escape') closeDrawer(); });
  if (drawer) {
    drawer.addEventListener('click', (e) => {
      if (e.target.closest('a')) closeDrawer();
    });
  }

  // Keep the popover anchored as the button moves
  window.addEventListener('resize', positionPopover, { passive: true });
  window.addEventListener('scroll', positionPopover, { passive: true });

  // --- Focus trap for accessibility ---
  let lastFocused = null;
  function getFocusable(root) {
    return [...root.querySelectorAll(
      'a[href], button:not([disabled]), [tabindex]:not([tabindex="-1"])'
    )].filter(el => el.offsetParent !== null);
  }
  function trapFocus(panel) {
    lastFocused = document.activeElement;
    const focusables = getFocusable(panel);
    const first = focusables[0], last = focusables[focusables.length - 1];
    if (first) first.focus();

    function handleTab(e) {
      if (e.key !== 'Tab') return;
      if (focusables.length === 0) return;
      if (e.shiftKey && document.activeElement === first) { e.preventDefault(); last.focus(); }
      else if (!e.shiftKey && document.activeElement === last) { e.preventDefault(); first.focus(); }
    }
    panel.__trapHandler = handleTab;
    document.addEventListener('keydown', handleTab);
  }
  function releaseFocus() {
    if (drawer && drawer.__trapHandler) {
      document.removeEventListener('keydown', drawer.__trapHandler);
      delete drawer.__trapHandler;
    }
    if (lastFocused) { lastFocused.focus({ preventScroll: true }); lastFocused = null; }
  }

  /* ----------------- Projects/Timeline loader ----------------- */
  fetch(`${baseurl}/projects.json`)
    .then(res => res.json())
    .then(data => {
      data.sort((a, b) => {
        const da = a.date === 'Coming Soon' ? -Infinity : new Date(a.date);
        const db = b.date === 'Coming Soon' ? -Infinity : new Date(b.date);
        return db - da;
      });

      const timeline = document.querySelector('.timeline');
      if (timeline) {
        timeline.innerHTML = '';
        data.forEach(proj => {
          const li = document.createElement('li');
          li.className = 'timeline-item';
          li.innerHTML = `
            <div class="timeline-icon-img">
              <img src="${proj.image}" alt="${proj.title}" />
            </div>
            <div class="timeline-content">
              <a href="${proj.url}">${proj.title}</a>
            </div>
            <span class="timeline-date">${
              proj.date === 'Coming Soon'
                ? 'Coming Soon'
                : new Date(proj.date).toLocaleDateString()
            }</span>`;
          timeline.appendChild(li);
        });
      }

      const grid = document.querySelector('.projects-grid');
      if (grid) {
        grid.innerHTML = '';
        data.forEach(proj => {
          const card = document.createElement('div');
          card.className = 'project-card';
          card.innerHTML = `
            <img src="${proj.thumbnail || proj.image}" alt="${proj.title}">
            <h3>${proj.title}</h3>
            <p>${proj.blurb}</p>
            <div class="read-more"><a href="${proj.url}">Read More</a></div>`;
          grid.appendChild(card);
        });
      }
    })
    .catch(console.error);

  /* ----------------- Résumé: dynamic sizing & mobile no-pan ----------------- */
  const frame = document.querySelector('.resume-container iframe');
  const container = document.querySelector('.resume-container');

  const isSmall = () => matchMedia('(max-width: 768px)').matches;

  // Use stable PDF page aspect ratio (US Letter ~ 8.5x11)
  const PAGE_W = 816;   // CSS px approximation at ~96dpi
  const PAGE_H = 1056;

  function setPdfSrc() {
    if (!frame) return;
    const clean = (frame.dataset.src || frame.getAttribute('src')).split('#')[0];
    frame.dataset.src = clean;
    // Desktop: page-fit; Mobile: force FitH but we scale the iframe itself
    const hash = isSmall() ? '#zoom=100&view=FitH' : '#zoom=page-fit&view=Fit';
    const want = `${clean}${hash}`;
    if (frame.src !== want) frame.src = want;
  }

  // Scale the iframe on small screens so it fits width perfectly and sets container height
  function applyMobileScale() {
    if (!frame || !container) return;

    if (!isSmall()) {
      // Desktop: fill container without extra transforms
      frame.style.transform = '';
      frame.style.width = '100%';
      frame.style.height = '100%';
      container.style.height = `calc(100svh - var(--header-h) - 20px)`;
      return;
    }

    // Width-fit scaling
    const availW = container.clientWidth;
    const scale  = availW / PAGE_W;

    // Give iframe its unscaled page size, then scale it down to fit width
    frame.style.width  = `${PAGE_W}px`;
    frame.style.height = `${PAGE_H}px`;
    frame.style.transform = `scale(${scale})`;
    frame.style.transformOrigin = 'top center';

    // Set container height to scaled page height so there's no inner scroll/pan
    const scaledH = Math.ceil(PAGE_H * scale);
    container.style.height = `${scaledH}px`;
  }

  function applyResumeBehavior() {
    setPdfSrc();
    applyMobileScale();
  }

  if (frame && container) {
    applyResumeBehavior();
    // Keep it responsive to viewport changes & orientation changes
    window.addEventListener('resize', applyResumeBehavior);
    window.addEventListener('orientationchange', applyResumeBehavior);

    // If fonts/UI chrome change the layout after load (iOS), observe size
    const ro = new ResizeObserver(applyResumeBehavior);
    ro.observe(container);
  }
});
