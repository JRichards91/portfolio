document.addEventListener('DOMContentLoaded', () => {
  // Toggle timeline orientation
  const tl  = document.querySelector('.timeline');
  const btn = document.getElementById('toggle-orientation');
  if (tl && btn) {
    btn.addEventListener('click', () => {
      tl.classList.toggle('vertical');
    });
  }
});
