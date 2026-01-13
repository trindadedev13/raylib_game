export DISPLAY=:0

make

termux-x11 :0 &

sleep 5

X11_PID=$!

cleanup() {
  kill -9 $X11_PID
}

trap cleanup INT TERM

make run

cleanup
