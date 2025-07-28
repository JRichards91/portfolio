document.addEventListener('DOMContentLoaded', () => {
  fetch('assets/data/projects.json')
    .then(res => res.json())
    .then(data => {
      // Sort by date descending
      data.sort((a, b) => new Date(b.date) - new Date(a.date));
      // Timeline
      const timeline = document.getElementById('timeline');
      if (timeline) {
        data.forEach(project => {
          const li = document.createElement('li');
          li.className = 'timeline-item';
          const icon = document.createElement('div');
          icon.className = 'timeline-icon';
          icon.textContent = project.title.charAt(0);
          li.appendChild(icon);
          const content = document.createElement('div');
          content.className = 'timeline-content';
          const a = document.createElement('a');
          a.href = project.url;
          a.textContent = project.title;
          content.appendChild(a);
          const date = document.createElement('span');
          date.className = 'timeline-date';
          date.textContent = new Date(project.date).toLocaleDateString();
          content.appendChild(date);
          li.appendChild(content);
          timeline.appendChild(li);
        });
      }
      // Projects Grid
      const grid = document.querySelector('.projects-grid');
      if (grid) {
        data.forEach(project => {
          const card = document.createElement('div');
          card.className = 'project-card';
          const img = document.createElement('img');
          img.src = project.image;
          img.alt = project.title;
          card.appendChild(img);
          const title = document.createElement('h3');
          title.textContent = project.title;
          card.appendChild(title);
          const blurb = document.createElement('p');
          blurb.textContent = project.blurb;
          card.appendChild(blurb);
          const link = document.createElement('a');
          link.href = project.url;
          link.textContent = 'Read More';
          card.appendChild(link);
          grid.appendChild(card);
        });
      }
    })
    .catch(err => console.error(err));
});