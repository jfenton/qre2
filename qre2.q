reximpl:`re2 2:(`PartialMatchN;2);
rexmatch:`re2 2:(`PartialMatch;2);

// apply a regex bearing named groups to a vector
rex: {
  r:reximpl[$[(type x)=0h;x;(type x)=11h;string x;enlist x];y];
  $[(count r)=(count x);:r;];
  k:r[0];
  v:1_r;
  flip (`input,`$k)!(flip (`$x),'v)
  };

// apply a regex to a vector, returns list of captures only
rexs: {
  reximpl[?[(type x)=0h;x;enlist x];y]
  };

rext: {[t;c;r]
  c xcol 1!rex[string ?[t;();();(?:;c)];r]
  };

// apply a regex to a vector, return a bool vector of matches only
rexm: {
  rexmatch[?[(type x)=0h;x;enlist x];y]
  };

