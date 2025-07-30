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
            <img src="${proj.image}" alt="${proj.title}">
            <h3>${proj.title}</h3>
            <p>${proj.blurb}</p>
            <a href="${proj.url}">Read More</a>`;
          grid.appendChild(card);
        });
      }
    })
    .catch(console.error);
});
