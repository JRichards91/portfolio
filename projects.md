---
layout: default
title: Projects
permalink: /projects/
---

{% include banner.html %}

<section class="projects-list">
  <h2>Projects</h2>
  <div class="projects-grid">
    {% assign data = site.data.projects | sort: 'date' | reverse %}
    {% for project in data %}
      <div class="project-card">
        <img src="{{ project.image | relative_url }}" alt="{{ project.title }}" />
        <h3>{{ project.title }}</h3>
        <p>{{ project.blurb }}</p>
        <a href="{{ project.url | relative_url }}">Read More</a>
      </div>
    {% endfor %}
  </div>
</section>
