---
layout: default
title: Home
---

<section class="hero">
  <h1>
    Engineering for Tomorrow,<br>
    One Innovation at a Time
  </h1>
  <p>Hi, I’m Justin Richards, an Electrical & Computer Engineer who brings embedded systems, 3D‑printed devices, and robotics to life. Explore my timeline to see projects from smart gardens to autonomous robots.</p>
</section>

<section class="timeline-section">
  <h2 style="text-align: center;">Projects Timeline</h2>
  <ul class="timeline">
    {% assign data = site.data.projects | sort: 'date' | reverse %}
    {% for project in data %}
      <li class="timeline-item">
        <div class="timeline-icon-img">
          <img src="{{ project.image | relative_url }}" alt="{{ project.title }} thumbnail">
        </div>
        <div class="timeline-content">
          <a href="{{ project.url | relative_url }}">{{ project.title }}</a>
        </div>
        <span class="timeline-date">
          {% if project.date == "Coming Soon" %}
            Coming Soon
          {% else %}
            {{ project.date | date: "%b %-d, %Y" }}
          {% endif %}
        </span>
      </li>
    {% endfor %}
  </ul>
</section>
