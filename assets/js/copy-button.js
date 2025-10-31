document.addEventListener('DOMContentLoaded', function() {
  document.querySelectorAll('pre[class^=\"nje-source-block\"]').forEach(function(el) {
    el.style.position = 'relative';
    var btn = document.createElement('button');
    btn.textContent = 'Copy';
    btn.className = 'nje-copy-btn';
    btn.onclick = function() {
        navigator.clipboard.writeText(el.textContent.trim());
        btn.textContent = 'Copied!';
        btn.style.background = '#b6e6b6';
        setTimeout(function() {
            btn.textContent = 'Copy';
            btn.style.background = '#f5faff';
        }, 1300);
    };
    el.appendChild(btn);
  });
});
