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
  <div class="timeline-centered">
    <div class="timeline-line"></div>
    <ul class="timeline-bubbles">
      {% assign data = site.data.projects | sort: 'date' | reverse %}
      {% for project in data %}
        {% cycle 'left', 'right' as side %}
        <li class="bubble {{ side }}">
          <div class="connector"></div>
          <div class="content">
            <img src="{{ project.image | relative_url }}" alt="{{ project.title }}">
            <div class="text">
              <p class="date">{{ project.date | date: "%b %-d, %Y" }}</p>
              <h3><a href="{{ project.url | relative_url }}">{{ project.title }}</a></h3>
              <p class="blurb">{{ project.blurb }}</p>
            </div>
          </div>
        </li>
      {% endfor %}
    </ul>
  </div>
</section>
