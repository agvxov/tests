# below me is not a comment
echo test
HISTTIMEFORMAT='%y/%m/%d %T: '
#1700000000
echo test
for i in *; do
    echo "a"
done
for i in *; do # harder
echo "ouch"
done
shopt -s lithist
for i in *; do
echo "ouch"
done
for i in *; do
#1700000000
echo "ouch"
done
