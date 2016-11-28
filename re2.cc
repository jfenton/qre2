#include <cstdlib>
#include <cstdio>
#include <iostream>

#include <re2/re2.h>
#include <re2/filtered_re2.h>

#include"k.h"

using namespace re2;
using namespace std;

extern "C" {

Z S makeErrStr(S s1,S s2){Z __thread char b[256];snprintf(b,256,"%s - %s",s1,s2);R b;}
Z __inline S c2s(S s,J n){S r=(S)malloc(n+1);R r?memcpy(r,s,n),r[n]=0,r:(S)krr((S)"wsfull (re2)");}
K PartialMatchN(K x,K y){

  S s,sy;K r;
  P(x->t&&x->t!=KC&&x->t!=KS&&x->t!=-KS||y->t!=KC,krr((S)"type"))
  U(sy=c2s((S)kC(y),y->n))
  RE2 pattern(sy,RE2::Quiet);
  free(sy);
  P(!pattern.ok(),krr(makeErrStr((S)"bad regex",(S)pattern.error().c_str())))
  const std::map<std::string,int> &grp_to_idx=pattern.NamedCapturingGroups();
  std::size_t args_count = pattern.NumberOfCapturingGroups();
  int mode = 0;
  if(args_count == grp_to_idx.size()) {
    mode = 1;
  } else if(args_count > 0 && grp_to_idx.size() == 0) {
    mode = 2;
  } else {
    R krr((S)"name groups or no pick one");
  }
  r=ktn(0,0);

  if(!x->t||x->t==KS){
    J i=0;
    // K r=ktn(KB,x->n);

    if(mode == 1) {
      K grs = ktn(0,0);
      std::map<std::string,int>::const_iterator iter_grps=grp_to_idx.cbegin();
      for(;iter_grps!=grp_to_idx.cend();++iter_grps) {
        #ifndef NBDEBUG
        cerr << "named group: " << iter_grps->first << endl;
        #endif
        K grp=kpn((char *)iter_grps->first.data(), iter_grps->first.length());
        jk(&grs, grp);
      }
      jk(&r, grs);
    }

    for(;i<x->n;i++){
      K z=0;
      P(!x->t&&(z=kK(x)[i])->t!=KC,(r0(r),krr((S)"type")))
      s=z?c2s((S)kC(z),z->n):kS(x)[i];P(!s,(r0(r),(K)0))

      std::vector<RE2::Arg> arguments(args_count);
      std::vector<RE2::Arg *> arguments_ptrs(args_count);
      std::vector<StringPiece> ws(args_count);

      for(std::size_t i = 0; i < args_count; ++i) {
        arguments[i] = &ws[i];
        arguments_ptrs[i] = &arguments[i];
      }

      StringPiece piece(s);
      /*kG(r)[i]=*/RE2::PartialMatchN(piece,pattern,&(arguments_ptrs[0]),args_count);

      std::map<std::string,int>::const_iterator iter_grps=grp_to_idx.cbegin();

      K rs = ktn(0,0);
      if(mode == 1) {
        for(;iter_grps!=grp_to_idx.cend();++iter_grps) {
          #ifndef NDEBUG
          cerr << "named group: " << iter_grps->first << " = " << ws[iter_grps->second-1].as_string() << " (" << iter_grps->second << ")"  << endl;
          #endif
          K cap=kpn((char *)ws[iter_grps->second-1].as_string().c_str(), ws[iter_grps->second-1].length());
          jk(&rs, cap);
        }
      } else if(mode == 2) {
        for(int i = 0; i < (int)args_count; ++i){
          #ifndef NDEBUG  
          cerr << "method 1 " << ws[i] << endl;
          #endif
          K cap=kpn((char *)ws[i].data(), ws[i].length());
          jk(&rs, cap);
        }
      }
      jk(&r, rs);

      if(z)free(s); // !!!
    }
    R r;
  } else { R krr((S)"list"); }
}

K PartialMatch(K x, K y)
{
  S s, sy;
  K r;
  P(x->t && x->t != KC && x->t != KS && x->t != -KS || y->t != KC, krr((S)"type"))
  U(sy = c2s((S)kC(y), y->n))
  RE2 pattern(sy, RE2::Quiet);
  free(sy);
  P(!pattern.ok(), krr(makeErrStr((S)"bad regex", (S)pattern.error().c_str())))
  if (!x->t || x->t == KS)
  {
    J i = 0;
    K r = ktn(KB, x->n);
    for (; i < x->n; i++)
    {
      K z = 0;
      P(!x->t && (z = kK(x)[i])->t != KC, (r0(r), krr((S)"type")))
      s = z ? c2s((S)kC(z), z->n) : kS(x)[i];
      P(!s, (r0(r), (K)0))
      kG(r)[i] = RE2::PartialMatch(s, pattern);
      if (z)
        free(s);
    }
    R r;
  }
  s = x->t == -KS ? x->s : c2s((S)kC(x), x->n);
  r = kb(RE2::PartialMatch(s, pattern));
  if (s != x->s)
    free(s);
  R r;
}

} // Extern C
