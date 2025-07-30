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
  <h2 class="timeline-title">Projects Timeline</h2>
  <div class="timeline-wrapper">
    <div class="timeline-line"></div>
    <ul class="timeline-alt">
      {% assign data = site.data.projects | sort: 'date' | reverse %}
      {% for project in data %}
        <li class="timeline-entry">
          <span class="timeline-dot"></span>
          <div class="timeline-bubble">
            <div class="timeline-date">{{ project.date | date: "%b %-d, %Y" }}</div>
            <div class="timeline-title"><a href="{{ project.url | relative_url }}">{{ project.title }}</a></div>
            <div class="timeline-blurb">{{ project.blurb }}</div>
          </div>
        </li>
      {% endfor %}
    </ul>
  </div>
</section>
