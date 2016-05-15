# Author  : Sujith Sudarshan
# Purpose : Takes the stored file records from Prj.dat and transforms them into a compatible
#           markdown page like kramdown.
#

import os.path
from string import Template

with open('Prj.dat') as f:
	content = [x.strip('\n').strip('#').split('|') for x in f.readlines()]

f.close()
for i in content:
	pname = i[0]
	print 'Project Name : '+pname
	nmemb = int(i[1])
	pmemb = [i[j+2] for j in range(nmemb)]
	print 'Team Members : '+str(pmemb)
	pdate = i[nmemb+2]
	print 'Date : '+pdate
	pdesc = i[nmemb+3]
	print 'Description : '+pdesc
	fname = pdate + ' ' + pname.lower() + '.md'
	fname = "-".join(fname.split())
	fname = '../_posts/'+fname
	print fname
	if os.path.isfile(fname):
		print 'File exits!'
		f=open(fname, 'r')
		f.readlines()
		f.close
	else:
		print 'No file!'
		post=Template("""
---
layout: post
title: "$PNAME"
date: $PDATE
---
Project Name : $PNAME
Team Members : $PMEMB
Description  : $PDESC
		""").substitute(PNAME=pname, PDATE=pdate, PMEMB=str(pmemb), PDESC=pdesc)
		print post
		f=open(fname, 'w')
		f.write(post)
		f.close
	print '\n'
