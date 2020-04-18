
// Product  KmsBase

/// \author	  KMS - Martin Dubois, ing.
/// \file     Includes/KmsLib/HTML5.h

#pragma once

// Includes
/////////////////////////////////////////////////////////////////////////////

// ===== C ==================================================================
#include <stdio.h>

namespace KmsLib
{

    namespace HTML5
    {

        // Functions / Fonctions
        /////////////////////////////////////////////////////////////////////

        void  Close(FILE * aFile);

        void  Complete(FILE * aFile);

        FILE  * Create(const char * aFolder, const char * aFile, const char * aTitle);

        FILE  * Open(const char * aFolder, const char * aFile);

        void  a       (FILE * aFile, const char * aRef, const char * aText);
        void  a_Begin (FILE * aFile, const char * aRef);
        void  a_End   (FILE * aFile);

        void  abbr       (FILE * aFile, const char * aTitle, const char * aText);
        void  abbr_Begin (FILE * aFile, const char * aTitle);
        void  abbr_End   (FILE * aFile);

        void  acronym       (FILE * aFile, const char * aTitle, const char * aText);
        void  acronym_Begin (FILE * aFile, const char * aTitle);
        void  acronym_End   (FILE * aFile);

        void  address       (FILE * aFile, const char * aText);
        void  address_Begin (FILE * aFile);
        void  address_End   (FILE * aFile);

        void  aside       (FILE * aFile, const char * aText);
        void  aside_Begin (FILE * aFile);
        void  aside_End   (FILE * aFile);

        void  b       (FILE * aFile, const char * aText);
        void  b_Begin (FILE * aFile);
        void  b_End   (FILE * aFile);

        void  big       (FILE * aFile, const char * aText);
        void  big_Begin (FILE * aFile);
        void  big_End   (FILE * aFile);

        void  blockquote       (FILE * aFile, const char * aCite, const char * aText);
        void  blockquote_Begin (FILE * aFile, const char * aCite);
        void  blockquote_End   (FILE * aFile);

        void  body_Begin (FILE * aFile);
        void  body_End   (FILE * aFile);

        void  br (FILE * aFile);

        void  caption       (FILE * aFile, const char * aText);
        void  caption_Begin (FILE * aFile);
        void  caption_End   (FILE * aFile);

        void  center       (FILE * aFile, const char * aText);
        void  center_Begin (FILE * aFile);
        void  center_End   (FILE * aFile);

        void  cite       (FILE * aFile, const char * aText);
        void  cite_Begin (FILE * aFile);
        void  cite_End   (FILE * aFile);

        void  code       (FILE * aFile, const char * aText);
        void  code_Begin (FILE * aFile);
        void  code_End   (FILE * aFile);

        void  dd       (FILE * aFile, const char * aText);
        void  dd_Begin (FILE * aFile);
        void  dd_End   (FILE * aFile);

        void  del       (FILE * aFile, const char * aText);
        void  del_Begin (FILE * aFile);
        void  del_End   (FILE * aFile);

        void  details_Begin (FILE * aFile);
        void  details_End   (FILE * aFile);

        void  dfn       (FILE * aFile, const char * aText);
        void  dfn_Begin (FILE * aFile);
        void  dfn_End   (FILE * aFile);

        void  div_Begin (FILE * aFile);
        void  div_End   (FILE * aFile);

        void  dl_Begin (FILE * aFile);
        void  dl_End   (FILE * aFile);

        void  dt       (FILE * aFile, const char * aText);
        void  dt_Begin (FILE * aFile);
        void  dt_End   (FILE * aFile);

        void  em       (FILE * aFile, const char * aText);
        void  em_Begin (FILE * aFile);
        void  em_End   (FILE * aFile);

        void  footer       (FILE * aFile, const char * aText);
        void  footer_Begin (FILE * aFile);
        void  footer_End   (FILE * aFile);

        void  h       (FILE * aFile, unsigned int aH, const char * aText);
        void  h_Begin (FILE * aFile, unsigned int aH);
        void  h_End   (FILE * aFile, unsigned int aH);

        void  head_Begin (FILE * aFile);
        void  head_End   (FILE * aFile);

        void  hr(FILE * aFile);

        void  html_Begin (FILE * aFile);
        void  html_End   (FILE * aFile);

        void  i       (FILE * aFile, const char * aText);
        void  i_Begin (FILE * aFile);
        void  i_End   (FILE * aFile);

        void  ins       (FILE * aFile, const char * aText);
        void  ins_Begin (FILE * aFile);
        void  ins_End   (FILE * aFile);

        void  kbd       (FILE * aFile, const char * aText);
        void  kbd_Begin (FILE * aFile);
        void  kbd_End   (FILE * aFile);

        void  li       (FILE * aFile, const char * aText);
        void  li_Begin (FILE * aFile);
        void  li_End   (FILE * aFile);

        void  main       (FILE * aFile, const char * aText);
        void  main_Begin (FILE * aFile);
        void  main_End   (FILE * aFile);

        void  mark       (FILE * aFile, const char * aText);
        void  mark_Begin (FILE * aFile);
        void  mark_End   (FILE * aFile);

        void  nav_Begin (FILE * aFile);
        void  nav_End   (FILE * aFile);

        void  ol_Begin (FILE * aFile);
        void  ol_End   (FILE * aFile);

        void  optgroup_Begin (FILE * aFile, const char * aLabel);
        void  optgroup_End   (FILE * aFile);

        void  option       (FILE * aFile, const char * aValue, const char * aText);
        void  option_Begin (FILE * aFile, const char * aValue);
        void  option_End   (FILE * aFile);

        void  p       (FILE * aFile, const char * aText);
        void  p_Begin (FILE * aFile);
        void  p_End   (FILE * aFile);

        void  pre       (FILE * aFile, const char * aText);
        void  pre_Begin (FILE * aFile);
        void  pre_End   (FILE * aFile);

        void  progress(FILE * aFile, unsigned int aValue, unsigned int aMax);

        void  q       (FILE * aFile, const char * aText);
        void  q_Begin (FILE * aFile);
        void  q_End   (FILE * aFile);

        void  s       (FILE * aFile, const char * aText);
        void  s_Begin (FILE * aFile);
        void  s_End   (FILE * aFile);

        void  samp       (FILE * aFile, const char * aText);
        void  samp_Begin (FILE * aFile);
        void  samp_End   (FILE * aFile);

        void  section_Begin (FILE * aFile);
        void  section_End   (FILE * aFile);

        void  select_Begin (FILE * aFile);
        void  select_End   (FILE * aFile);

        void  small       (FILE * aFile, const char * aText);
        void  small_Begin (FILE * aFile);
        void  small_End   (FILE * aFile);

        void  span       (FILE * aFile, const char * aStyle, const char * aText);
        void  span_Begin (FILE * aFile, const char * aStyle);
        void  span_End   (FILE * aFile);

        void  strike       (FILE * aFile, const char * aText);
        void  strike_Begin (FILE * aFile);
        void  strike_End   (FILE * aFile);

        void  strong       (FILE * aFile, const char * aText);
        void  strong_Begin (FILE * aFile);
        void  strong_End   (FILE * aFile);

        void  style(FILE * aFile, const char * aText);
        void  style_Begin(FILE * aFile);
        void  style_End(FILE * aFile);

        void  sub       (FILE * aFile, const char * aText);
        void  sub_Begin (FILE * aFile);
        void  sub_End   (FILE * aFile);

        void  summary       (FILE * aFile, const char * aText);
        void  summary_Begin (FILE * aFile);
        void  summary_End   (FILE * aFile);

        void  sup       (FILE * aFile, const char * aText);
        void  sup_Begin (FILE * aFile);
        void  sup_End   (FILE * aFile);

        void  table_Begin (FILE * aFile);
        void  table_End   (FILE * aFile);

        void  tbody_Begin (FILE * aFile);
        void  tbody_End   (FILE * aFile);

        void  td       (FILE * aFile, const char * aText);
        void  td_Begin (FILE * aFile);
        void  td_End   (FILE * aFile);

        void  tfoot_Begin (FILE * aFile);
        void  tfoot_End   (FILE * aFile);

        void  th       (FILE * aFile, const char * aText);
        void  th_Begin (FILE * aFile);
        void  th_End   (FILE * aFile);

        void  thead_Begin (FILE * aFile);
        void  thead_End   (FILE * aFile);

        void  title       (FILE * aFile, const char * aText);
        void  title_Begin (FILE * aFile);
        void  title_End   (FILE * aFile);

        void  tr_Begin (FILE * aFile);
        void  tr_End   (FILE * aFile);

        void  u       (FILE * aFile, const char * aText);
        void  u_Begin (FILE * aFile);
        void  u_End   (FILE * aFile);

        void  ul_Begin (FILE * aFile);
        void  ul_End   (FILE * aFile);

        void  var       (FILE * aFile, const char * aText);
        void  var_Begin (FILE * aFile);
        void  var_End   (FILE * aFile);

        void  DOCTYPE(FILE * aFile);

        void  Comment       (FILE * aFile, const char * aText);
        void  Comment_Begin (FILE * aFile);
        void  Comment_End   (FILE * aFile);

        void  Tag             (FILE * aFile, const char * aTag);
        void  Tag             (FILE * aFile, const char * aTag, const char * aAttr);
        void  Tag_Begin       (FILE * aFile, const char * aTag);
        void  Tag_Begin       (FILE * aFile, const char * aTag, const char * aAttr);
        void  Tag_Begin_Begin (FILE * aFile, const char * aTag);
        void  Tag_Begin_End   (FILE * aFile);
        void  Tag_End         (FILE * aFile);
        void  Tag_End         (FILE * aFile, const char * aTag);

    }
}
