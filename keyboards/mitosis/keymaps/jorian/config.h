#ifndef CONFIG_USER_H
#define CONFIG_USER_H

#include "../../config.h"

#define LAYOUT_jorian( \
k42, k31,  k00, k01, k02, k03, k04,      k05, k06, k07, k08, k09, k38, k47, \
     k44,  k10, k11, k12, k13, k14,      k15, k16, k17, k18, k19, k45, \
     k43,  k20, k21, k22, k23, k24,      k25, k26, k27, k28, k29, k46, \
                     k33, k34, k32,      k37, k35, k36 \
) \
{ \
    { k00,   k01, k02, k03, k04,      k05, k06, k07, k08, k09   }, \
    { k10,   k11, k12, k13, k14,      k15, k16, k17, k18, k19   }, \
    { k20,   k21, k22, k23, k24,      k25, k26, k27, k28, k29   }, \
    { KC_NO, k31, k32, k33, k34,      k35, k36, k37, k38, KC_NO },  \
    { KC_NO, KC_NO, k42, k43, k44,    k45, k46, k47, KC_NO, KC_NO } \
}

#endif //CONFIG_USER_H
