document.addEventListener('DOMContentLoaded', () => {
  // Load projects/timeline from JSON
  fetch('/portfolio/projects.json')
    .then(res => res.json())
    .then(data => {
      data.sort((a, b) => new Date(b.date) - new Date(a.date));

      // Timeline (index.md)
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
            <span class="timeline-date">${new Date(proj.date).toLocaleDateString()}</span>`;
          timeline.appendChild(li);
        });
      }

      // Projects Grid (projects.md)
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
            <a href="${proj.url}">Read More</a>`;
          grid.appendChild(card);
        });
      }
    })
    .catch(console.error);
});

// --- Mobile nav toggle (phones only) ---
(function () {
  const toggle = document.querySelector('.nav-toggle');
  const panel  = document.getElementById('mobile-menu');
  if (!toggle || !panel) return;

  function closeMenu() {
    panel.classList.remove('open');
    document.body.classList.remove('menu-open');
    toggle.setAttribute('aria-expanded', 'false');
  }

  function openMenu() {
    panel.classList.add('open');
    document.body.classList.add('menu-open');
    toggle.setAttribute('aria-expanded', 'true');
  }

  toggle.addEventListener('click', () => {
    const isOpen = panel.classList.contains('open');
    isOpen ? closeMenu() : openMenu();
  });

  // Close when tapping a link
  panel.addEventListener('click', (e) => {
    if (e.target.closest('a')) closeMenu();
  });

  // ESC key closes menu
  document.addEventListener('keydown', (e) => {
    if (e.key === 'Escape') closeMenu();
  });

  // Resize back to desktop
  window.addEventListener('resize', () => {
    if (window.innerWidth > 768) closeMenu();
  });
})();
