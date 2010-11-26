#!/bin/sh
modules="err str firecrow"

build(){
	mkdir -p ./build;
	mkdir -p ./build/objects;
	hname=./build/firecrow.h;
	tmph=${hname}.tmp;
	echo "/* "$(date +%F)" */" > $tmph;
	objs="";
	for m in $modules; do
		if [ -f ${m}.h ]; then
			echo -e "\n/* ==== ${m} ==== */\n\n" >> $tmph;
			cat ${m}.h >> $tmph; 
		fi
		mpath="./build/objects/${m}.o"
		cc -c -o ${mpath}  ${m}.c;
		objs=${objs}" "${mpath}
	done
	mv $tmph $hname 
	ar -cvq ./build/libfirecrow.a ${objs} 
}

clean(){
	rm -vf ./build/libfirecrow.a
	rm -vf ./build/objects/*.o
}

install(){
	cp -v ./build/libfirecrow.a /usr/lib/
	cp -v ./build/firecrow.h /usr/include/
}

case $1 in
	"" | "-b" | "build")
		clean; build;;
	"-c" | "clean")
		clean;;
  "-i" | "install")
	install;;
esac;
