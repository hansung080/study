package main

import (
	"fmt"
	"time"
	"sync/atomic"
)

func main() {
	cnt := int64(10)

	for i := 0; i < 10; i++ {
		go func() {
			//cnt--
			atomic.AddInt64(&cnt, -1)
		}()
	}

	//for cnt > 0 {
	for atomic.LoadInt64(&cnt) > 0 {
		time.Sleep(100 * time.Millisecond)
	}

	fmt.Println(cnt)
}

