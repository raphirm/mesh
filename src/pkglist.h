#ifndef __PKGLIST_H__
#define __PKGLIST_H__
struct pkglist *pkg_add(struct pkglist *, unsigned short id , unsigned char target);
void pkg_addNextHop(struct pkglist *, struct nodelist *);
void pkg_remove(struct pkglist *, unsigned short id , unsigned char target);
struct pkglist *pkg_search(struct pkglist *, unsigned short id , unsigned char target);
void pkg_list(struct pkglist *);
#endif
