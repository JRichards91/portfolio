---
layout: default
title: Home
---

<section class="hero reveal">
  <h1>
    I Build Embedded Systems<br>and Robots That Work
  </h1>
  <p>I'm Justin Richards, an Electrical & Computer Engineer. I like taking a project from a schematic to a working prototype — soil sensors, hydroponics rigs, robots with arms, whatever's in front of me. Below is a timeline of what I've built, roughly in the order I built it.</p>
  <div class="btn-row">
    <a class="btn btn-primary" href="{{ '/projects/' | relative_url }}">View Projects</a>
    <a class="btn btn-outline" href="{{ '/resume/' | relative_url }}">Résumé</a>
  </div>
</section>

<section class="timeline-section">
  <h2 style="text-align: center;">Projects Timeline</h2>
  <ul class="timeline">
    {% assign data = site.data.projects | sort: 'date' | reverse %}
    {% for project in data %}
      <li class="timeline-item reveal">
        <div class="timeline-icon-img">
          <img src="{{ project.image | relative_url }}" alt="{{ project.title }} thumbnail">
        </div>
        <div class="timeline-content">
          <a href="{{ project.url | relative_url }}">{{ project.title }}</a>
        </div>
        <span class="timeline-date">
          {% if project.date == "Coming Soon" %}
            <span class="badge">Coming Soon</span>
          {% else %}
            {{ project.date | date: "%b %-d, %Y" }}
          {% endif %}
        </span>
      </li>
    {% endfor %}
  </ul>
</section>
