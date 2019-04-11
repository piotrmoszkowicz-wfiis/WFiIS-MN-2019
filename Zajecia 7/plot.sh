FILES=`find ./ -name "plotn*.png" -print0 | xargs -0 ls`
for i in $(echo $FILES | tr " " "\n")
do
    rm $i
done

FILES_PLOT=`find ./ -name "plotn*" -print0 | xargs -0 ls`
for i in $(echo $FILES_PLOT | tr " " "\n")
do
    gnuplot $i
done