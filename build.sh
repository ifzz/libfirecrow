#!/bin/sh
modules="arr err util table"

build(){
  mkdir -p ./build;
  mkdir -p ./build/objects;
  hname=./build/firecrow.h;
  tmph=${hname}.tmp;
  echo "/* "$(date +%F)" */" > $tmph;
  objs="";
  for m in $modules; do
		header=''
		echo ">>> compiling: $m >>>"
    if [ -f ${m}.h ]; then
      echo -e "\n/* ==== ${m} ==== */\n\n" >> $tmph;
      cat ${m}.h >> $tmph; 
    fi
    mpath="./build/objects/${m}.o"
    cc -c -o ${mpath} ${m}.c -DDEBUG;
    objs=${objs}" "${mpath}
  done
  mv $tmph $hname 
  ar -cvq ./build/libfirecrow.a ${objs} 

  #build test 
  cc -o ./build/test $objs test.c;
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
