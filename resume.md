---
layout: default
title: Resume
permalink: /resume/
full_bleed: true
resume_pdf: /assets/resume/Justin_Richards_Resume_Redacted.pdf
---

<section class="resume-embed">
  <div class="resume-toolbar">
    <a
      class="btn btn-download"
      href="{{ page.resume_pdf | relative_url }}"
      download
      aria-label="Download resume (redacted PDF)"
    >
      Download PDF
    </a>
    <span class="resume-note">Public redacted version</span>
  </div>

  <div class="resume-container">
    <iframe
      title="Justin Richards — Resume (Redacted)"
      src="{{ page.resume_pdf | relative_url }}#view=FitH"
    ></iframe>
  </div>
</section>
