vector<string> duval(string const& s) {
  int n = s.size(), i = 0;
  vector<string> fac;
  while (i < n) {
    int j = i + 1, k = i;
    while (j < n && s[k] <= s[j]) {
      if (s[k] < s[j]) k = i;
      else k++;
      j++;
    }
    while (i <= k) fac.eb(s.substr(i, j - k)), i += j - k;
  }
  return fac;
}