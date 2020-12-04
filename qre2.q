
.qre2:((`$":qre2_l64") 2:(`qre2;1))`;

\d .qre2

reximpl:.qre2.reximpl;
rexmatch:.qre2.rexmatch;

// apply a regex bearing named groups to a vector
rex: {
  r:.qre2.reximpl[$[(type x)=0h;x;(type x)=11h;string x;enlist x];y];
  $[(count r)=(count x);:r;];
  k:r[0];
  v:1_r;
  flip (`input,`$k)!(flip (`$x),'v)
  };

// apply a regex to a vector, returns list of captures only
rexs: {
  qre2.reximpl[?[(type x)=0h;x;enlist x];y]
  };

rext: {[t;c;r]
  c xcol 1!.qre2.rex[string ?[t;();();(?:;c)];r]
  };

// apply a regex to a vector, return a bool vector of matches only
rexm: {
  .qre2.rexmatch[?[(type x)=0h;x;enlist x];y]
  };

\d .
