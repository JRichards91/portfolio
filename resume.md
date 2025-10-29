---
layout: default
title: Resume
permalink: /resume/
resume_pdf: /assets/files/Justin Richards Résumé.pdf
---

<section class="resume-embed">
  <!-- Desktop: native PDF viewer (hidden on iOS/small by JS) -->
  <div class="resume-container">
    <iframe
      title="Justin Richards — Resume"
      src="{{ page.resume_pdf | relative_url }}"
      data-src="{{ page.resume_pdf | relative_url }}"
      loading="lazy"
    ></iframe>
  </div>

  <!-- Mobile/iOS: PDF.js canvas renderer -->
  <div
    id="pdfjs-view"
    class="pdfjs-view"
    data-pdf="{{ page.resume_pdf | relative_url }}"
    hidden
  >
    <div class="pdfjs-pages" aria-live="polite"></div>
  </div>
</section>

<!-- Load PDF.js only on this page -->
<script src="https://cdn.jsdelivr.net/npm/pdfjs-dist@3.11.174/build/pdf.min.js"></script>
<script>
  pdfjsLib.GlobalWorkerOptions.workerSrc =
    "https://cdn.jsdelivr.net/npm/pdfjs-dist@3.11.174/build/pdf.worker.min.js";
</script>
