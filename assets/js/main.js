document.addEventListener('DOMContentLoaded', () => {
  /* ------------ Dropdown (burger) ------------ */
  const baseurl = document.documentElement.getAttribute('data-baseurl') || '';
  const burger = document.querySelector('.burger');
  const drawer = document.getElementById('mobile-drawer');
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
    backdrop.offsetHeight;
    backdrop.classList.add('is-visible');
  };
  const hideBackdrop = () => { if (backdrop) backdrop.classList.remove('is-visible'); };

  const openDrawer = () => {
    if (!burger || !drawer) return;
    positionPopover();
    burger.setAttribute('aria-expanded', 'true');
    drawer.classList.add('is-open');
    drawer.setAttribute('aria-hidden', 'false');
    showBackdrop();
  };
  const closeDrawer = () => {
    if (!burger || !drawer) return;
    burger.setAttribute('aria-expanded', 'false');
    drawer.classList.remove('is-open');
    drawer.setAttribute('aria-hidden', 'true');
    hideBackdrop();
  };

  if (backdrop) {
    backdrop.addEventListener('transitionend', () => {
      if (!backdrop.classList.contains('is-visible')) backdrop.hidden = true;
    });
  }
  if (burger) {
    burger.addEventListener('click', () => {
      const expanded = burger.getAttribute('aria-expanded') === 'true';
      expanded ? closeDrawer() : openDrawer();
    });
  }
  if (backdrop) backdrop.addEventListener('click', closeDrawer);
  if (drawer) {
    drawer.addEventListener('click', (e) => {
      const a = e.target.closest('a');
      if (a) closeDrawer();
    });
  }
  document.addEventListener('keydown', (e) => { if (e.key === 'Escape') closeDrawer(); });
  window.addEventListener('resize', () => { positionPopover(); });
  window.addEventListener('scroll', () => { positionPopover(); }, { passive: true });

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

  /* ----------------- RESUME: Mobile centering & scaling polyfill ----------------- */
  const frame = document.querySelector('.resume-container iframe');
  const container = document.querySelector('.resume-container');

  function isSmall() { return window.matchMedia('(max-width: 768px)').matches; }

  function setPdfSrc() {
    if (!frame) return;
    const clean = (frame.dataset.src || frame.getAttribute('src')).split('#')[0];
    frame.dataset.src = clean;
    // Desktop uses page-fit; mobile we’ll scale the iframe ourselves (native zoom ignored)
    const hash = isSmall() ? '#zoom=100&view=FitH' : '#zoom=page-fit&view=Fit';
    const want = `${clean}${hash}`;
    if (frame.src !== want) frame.src = want;
  }

  // Scale the iframe itself on mobile to fit width & center
  function scaleIframeForMobile() {
    if (!frame || !container) return;
    if (!isSmall()) {
      // reset on desktop
      frame.style.transform = '';
      frame.style.width = '100%';
      frame.style.height = '100%';
      container.style.height = `calc(100dvh - var(--header-h) - 20px)`;
      return;
    }

    // Assume US Letter page about 816x1056 CSS px at ~96dpi (good approximation)
    const baseW = 816;   // px
    const baseH = 1056;  // px
    const pad = 0;

    const availW = container.clientWidth - pad;
    const scale = availW / baseW;

    // Size the iframe to the unscaled page, then scale down to fit device width
    frame.style.width = `${baseW}px`;
    frame.style.height = `${baseH}px`;
    frame.style.transform = `scale(${scale})`;
    frame.style.transformOrigin = 'top center';

    // Set container height to the scaled height so no clipping occurs
    const scaledH = Math.ceil(baseH * scale);
    container.style.height = `${scaledH}px`;
  }

  function applyPdfBehavior() {
    setPdfSrc();
    scaleIframeForMobile();
  }

  if (frame && container) {
    applyPdfBehavior();
    window.addEventListener('resize', applyPdfBehavior);
    window.addEventListener('orientationchange', applyPdfBehavior);
  }
});
