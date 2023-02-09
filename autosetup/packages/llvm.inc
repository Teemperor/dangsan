echo "building LLVM"
cd "$PATHAUTOPACKSRC"
[ -d llvm-svn/.git ] || run git clone https://github.com/llvm/llvm-project.git llvm-svn && git -C llvm-svn checkout 43dff0c03324bd8aa2dfa93062db8597ea43f07b

cd "$PATHAUTOPACKSRC/llvm-svn/projects/compiler-rt"
if [ ! -f .autosetup.patched-COMPILERRT-safestack ]; then
	run patch -p0 < "$PATHROOT/patches/COMPILERRT-safestack-$VERSIONLLVMPATCH.diff"
	touch .autosetup.patched-COMPILERRT-safestack
fi
cd "$PATHAUTOPACKSRC/llvm-svn"
if [ ! -f .autosetup.patched-LLVM-gold-plugins ]; then
	run patch -p0 < "$PATHROOT/patches/LLVM-gold-plugins-$VERSIONLLVMPATCH.diff"
	touch .autosetup.patched-LLVM-gold-plugins
fi
if [ ! -f .autosetup.patched-LLVM-safestack ]; then
	run patch -p0 < "$PATHROOT/patches/LLVM-safestack-$VERSIONLLVMPATCH.diff"
	touch .autosetup.patched-LLVM-safestack
fi
run mkdir -p "$PATHAUTOPACKSRC/llvm-svn/obj"
cd "$PATHAUTOPACKSRC/llvm-svn/obj"
[ -f Makefile ] || run cmake -DCMAKE_INSTALL_PREFIX="$PATHAUTOPREFIX" -DCMAKE_BUILD_TYPE=Release -DLLVM_ENABLE_ASSERTIONS=ON -DLLVM_BINUTILS_INCDIR="$PATHBINUTILS/include" "$PATHAUTOPACKSRC/llvm-svn"
run make -j"$JOBS"
run make install
