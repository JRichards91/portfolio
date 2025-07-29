---
layout: default
title: Home
---
<section class="hero">
  <h1>Welcome to My Portfolio</h1>
  <p>I’m Justin Richards, an Electrical & Computer Engineer passionate about embedded systems, 3D printing, and automation. Browse the timeline below to see my latest work.</p>
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
