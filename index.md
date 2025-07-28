---
layout: default
title: Home
---
<section class="hero">
  <img src="{{ '/assets/img/profile.jpg' | relative_url }}" alt="Justin Richards" class="profile-img" />
  <h1>Welcome to My Portfolio</h1>
  <p>I’m an Electrical & Computer Engineer with a passion for designing embedded systems, custom PCBs, and automated robotics.  Explore my dynamic timeline below.</p>
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
          <span class="timeline-date">{{ project.date | date: "%B %-d, %Y" }}</span>
        </div>
      </li>
    {% endfor %}
  </ul>
</section>