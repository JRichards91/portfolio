---
layout: default
title: Home
---
<section class="hero">
  <h1>
    Engineering Tomorrow,<br/>
    One Innovation at a Time
  </h1>
  <p>Hi, I’m Justin Richards—an Electrical & Computer Engineer blending embedded systems, 3D printing, and robotics into real‑world solutions. Dive into my timeline below to explore hands‑on projects that range from hydroponic farms to autonomous robots.</p>
</section>

<section class="timeline-section">
  <h2>Timeline</h2>
  <ul class="timeline">
    {% assign data = site.data.projects | sort: 'date' | reverse %}
    {% for project in data %}
      <li class="timeline-item">
        <div class="timeline-icon">{{ project.title | slice: 0, 1 }}</div>
        <div class="timeline-content">
          <a href="{{ project.url | relative_url }}">{{ project.title }}</a>
        </div>
        <span class="timeline-date">{{ project.date | date: "%b %-d, %Y" }}</span>
      </li>
    {% endfor %}
  </ul>
</section>
