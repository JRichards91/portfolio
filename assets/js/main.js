document.addEventListener('DOMContentLoaded', () => {
  /* ------------ Dropdown popover positioning for burger ------------ */
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
    backdrop.offsetHeight; // reflow
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

  /* ----------------- PDF: auto-fit desktop vs mobile ----------------- */
  const resumeIframe = document.querySelector('.resume-container iframe');
  if (resumeIframe) {
    // store clean src without hash once
    const initialSrc = resumeIframe.getAttribute('src').split('#')[0];
    resumeIframe.dataset.src = initialSrc;

    const applyPdfFit = () => {
      const small = window.matchMedia('(max-width: 768px)').matches;
      // On mobile, browsers (esp. iOS Safari) ignore page-fit; use page-width to auto-scale and center.
      const hash = small ? '#zoom=page-width&view=FitH' : '#zoom=page-fit&view=Fit';
      // Only change if needed to avoid reload loops
      const want = `${resumeIframe.dataset.src}${hash}`;
      if (resumeIframe.src !== want) resumeIframe.src = want;
    };

    applyPdfFit();
    window.addEventListener('resize', applyPdfFit);
    window.addEventListener('orientationchange', applyPdfFit);
  }
});
