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

  /* ----------------- Résumé: dynamic sizing (desktop iframe) ----------------- */
  const frame = document.querySelector('.resume-container iframe');
  const container = document.querySelector('.resume-container');

  const isSmall = () => matchMedia('(max-width: 768px)').matches;

  // Use stable PDF page aspect ratio (US Letter ~ 8.5x11)
  const PAGE_W = 816;   // CSS px approximation at ~96dpi
  const PAGE_H = 1056;

  function setPdfSrc() {
    if (!frame) return;
    const clean = (frame.dataset.src || frame.getAttribute('src') || '').split('#')[0];
    if (!clean) return;
    frame.dataset.src = clean;
    const hash = isSmall() ? '#zoom=100&view=FitH' : '#zoom=page-fit&view=Fit';
    const want = `${clean}${hash}`;
    if (frame.src !== want) frame.src = want;
  }

  function applyMobileScale() {
    if (!frame || !container) return;

    if (!isSmall()) {
      frame.style.transform = '';
      frame.style.width = '100%';
      frame.style.height = '100%';
      container.style.height = `calc(100svh - var(--header-h) - 20px)`;
      return;
    }

    const availW = container.clientWidth;
    const scale  = availW / PAGE_W;

    frame.style.width  = `${PAGE_W}px`;
    frame.style.height = `${PAGE_H}px`;
    frame.style.transform = `scale(${scale})`;
    frame.style.transformOrigin = 'top center';

    const scaledH = Math.ceil(PAGE_H * scale);
    container.style.height = `${scaledH}px`;
  }

  function applyResumeBehavior() {
    setPdfSrc();
    applyMobileScale();
  }

  if (frame && container) {
    applyResumeBehavior();
    window.addEventListener('resize', applyResumeBehavior);
    window.addEventListener('orientationchange', applyResumeBehavior);

    const ro = new ResizeObserver(applyResumeBehavior);
    ro.observe(container);
  }
});

/* ---------- Résumé: use PDF.js on iOS / small screens so it fits with no panning ---------- */
(function(){
  const iframeWrap = document.querySelector('.resume-container');
  const iframe = iframeWrap && iframeWrap.querySelector('iframe');
  const pdfView = document.getElementById('pdfjs-view');
  if (!iframe || !pdfView) return;

  const isIOS = () => {
    const ua = navigator.userAgent;
    const iOS = /iPad|iPhone|iPod/.test(ua);
    const isMacTouch = /Macintosh/.test(ua) && 'ontouchend' in document;
    return iOS || isMacTouch;
  };
  const isSmall = () => matchMedia('(max-width: 768px)').matches;

  const shouldUsePdfJS = () => isIOS() || isSmall();

  async function renderWithPdfJS() {
    if (!shouldUsePdfJS()) return false;

    iframeWrap.hidden = true;
    pdfView.hidden = false;

    const pdfUrl = pdfView.getAttribute('data-pdf');
    const container = pdfView.querySelector('.pdfjs-pages');

    if (container.dataset.rendered === '1') {
      sizeToWidth();
      return true;
    }

    const pdf = await pdfjsLib.getDocument(pdfUrl).promise;

    for (let p = 1; p <= pdf.numPages; p++) {
      const page = await pdf.getPage(p);
      const viewport = page.getViewport({ scale: 1 });
      const canvas = document.createElement('canvas');
      const ctx = canvas.getContext('2d');

      const targetWidth = Math.min(1100, document.documentElement.clientWidth);
      const scale = targetWidth / viewport.width;
      const scaled = page.getViewport({ scale });

      canvas.width = Math.floor(scaled.width);
      canvas.height = Math.floor(scaled.height);

      await page.render({ canvasContext: ctx, viewport: scaled }).promise;
      container.appendChild(canvas);
    }

    container.dataset.rendered = '1';
    sizeToWidth();
    return true;
  }

  function sizeToWidth() {
    if (pdfView.hidden) return;
    const canvases = pdfView.querySelectorAll('canvas');
    if (!canvases.length) return;
    // CSS handles fluid width; forcing reflow keeps height in sync on iOS chrome changes
    // eslint-disable-next-line no-unused-expressions
    pdfView.offsetHeight;
  }

  function useIframeDesktop() {
    if (!shouldUsePdfJS()) {
      iframeWrap.hidden = false;
      pdfView.hidden = true;

      const src = (iframe.dataset.src || iframe.getAttribute('src') || '').split('#')[0];
      if (src) {
        iframe.dataset.src = src;
        const hash = '#zoom=page-fit&view=Fit';
        const want = `${src}${hash}`;
        if (iframe.src !== want) iframe.src = want;
      }
    }
  }

  (async () => {
    const usedPdf = await renderWithPdfJS();
    if (!usedPdf) useIframeDesktop();
  })();

  let resizeRAF = null;
  const onResize = () => {
    if (resizeRAF) cancelAnimationFrame(resizeRAF);
    resizeRAF = requestAnimationFrame(async () => {
      if (shouldUsePdfJS()) {
        await renderWithPdfJS();
      } else {
        useIframeDesktop();
      }
    });
  };
  window.addEventListener('resize', onResize);
  window.addEventListener('orientationchange', onResize);
})();
