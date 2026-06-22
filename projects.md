---
layout: default
title: Projects
permalink: /projects/
---

<section class="projects-list">
  <div class="projects-grid">
    {% assign data = site.data.projects | sort: 'date' | reverse %}
    {% for project in data %}
      <div class="project-card reveal">
        <img src="{{ project.thumbnail | default: project.image | relative_url }}" alt="{{ project.title }}" />
        <div class="project-card-body">
          <h3>{{ project.title }}</h3>
          {% assign status_slug = project.status | downcase | replace: " ", "-" %}
          <div class="card-tags">
            <span class="badge badge-status-{{ status_slug }}">{{ project.status }}</span>
            {% for tag in project.tags limit:3 %}
              <span class="badge badge-tag">{{ tag }}</span>
            {% endfor %}
          </div>
          <p>{{ project.blurb }}</p>
          <div class="read-more">
            <a href="{{ project.url | relative_url }}">Read More</a>
          </div>
        </div>
      </div>
    {% endfor %}
  </div>
</section>
