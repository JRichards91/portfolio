---
layout: default
title: Contact
permalink: /contact/
---

<section class="contact-form container">
  <h2>Get in Touch</h2>
  <form action="https://formspree.io/f/yourFormID" method="POST">
    <label>
      Name
      <input type="text" name="name" placeholder="Your name" required>
    </label>
    <label>
      Email
      <input type="email" name="email" placeholder="you@example.com" required>
    </label>
    <label>
      Subject
      <input type="text" name="subject" placeholder="Subject" required>
    </label>
    <label>
      Message
      <textarea name="message" rows="6" placeholder="Your message" required></textarea>
    </label>
    <button type="submit">Send Message</button>
  </form>
</section>
