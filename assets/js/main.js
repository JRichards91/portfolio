document.addEventListener('DOMContentLoaded', () => {
  /* ------------ Choose ONE mode: 'compact-right' | 'bottom-sheet' | 'fullscreen' | 'dropdown' ------------ */
  const DRAWER_MODE = 'dropdown'; // <— change this value to try another mode
  document.body.dataset.drawer = DRAWER_MODE;

  /* ----------------- Base URL helper ----------------- */
  const baseurl = document.documentElement.getAttribute('data-baseurl') || '';

  /* ----------------- Elements ----------------- */
  const burger = document.querySelector('.burger');
  const drawer = document.getElementById('mobile-drawer');
  const backdrop = document.querySelector('.drawer-backdrop');

  /* ----------------- Drawer helpers ----------------- */
  const showBackdrop = () => {
    if (!backdrop) return;
    backdrop.hidden = false;
    // force reflow so transition starts
    // eslint-disable-next-line no-unused-expressions
    backdrop.offsetHeight;
    backdrop.classList.add('is-visible');
  };
  const hideBackdrop = () => {
    if (!backdrop) return;
    backdrop.classList.remove('is-visible');
  };

  const openDrawer = () => {
    if (!burger || !drawer) return;
    burger.setAttribute('aria-expanded', 'true');
    drawer.classList.add('is-open');
    drawer.setAttribute('aria-hidden', 'false');
    document.body.classList.add('noscroll');
    showBackdrop();
  };

  const closeDrawer = () => {
    if (!burger || !drawer) return;
    burger.setAttribute('aria-expanded', 'false');
    drawer.classList.remove('is-open');
    drawer.setAttribute('aria-hidden', 'true');
    document.body.classList.remove('noscroll');
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
      if (a) closeDrawer(); // close on nav click
    });
  }
  document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape') closeDrawer();
  });
  window.addEventListener('resize', () => {
    if (window.innerWidth >= 992) closeDrawer();
  });

  /* ----------------- Load projects/timeline from JSON ----------------- */
  fetch(`${baseurl}/projects.json`)
    .then(res => res.json())
    .then(data => {
      data.sort((a, b) => {
        const da = a.date === 'Coming Soon' ? -Infinity : new Date(a.date);
        const db = b.date === 'Coming Soon' ? -Infinity : new Date(b.date);
        return db - da;
      });

      // Timeline
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

      // Projects Grid
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
});
