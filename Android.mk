dirs := \
	gl2_basic \
	gl_basic \
	include \
	lib \
	textures \

include $(call all-named-subdir-makefiles, $(dirs))
