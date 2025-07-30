---
layout: default
title: Contact
permalink: /contact/
---

<section class="contact-form container">
  <form action="https://formspree.io/f/xpwlrobv" method="POST">
    <!-- honeypot to deter spam -->
    <input type="text" name="_gotcha" style="display:none">

    <!-- where replies should go -->
    <input type="hidden" name="_replyto" value="you@yourdomain.com">

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
      <input type="text" name="subject" placeholder="Subject (optional)">
    </label>

    <label>
      Message  
      <textarea name="message" rows="6" placeholder="Your message" required></textarea>
    </label>

    <button type="submit">Send Message</button>
  </form>
</section>
