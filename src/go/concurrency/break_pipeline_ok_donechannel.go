package main

import (
	"fmt"
	"runtime"
	"time"
)

func PlusOne(done <-chan struct{}, in <-chan int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for num := range in {
			select {
			case out <- num + 1:
			case <-done:
				return	
			}
		}
	}()

	return out
}

func main() {
	c := make(chan int)
	go func() {
		defer close(c)
		for i := 3; i < 103; i +=10 {
			c <- i
		}
	}()

	done := make(chan struct{})
	nums := PlusOne(done, PlusOne(done, PlusOne(done, PlusOne(done, PlusOne(done, c)))))

	for num := range nums {
		fmt.Println("num:", num)
		if num == 18 {
			break
		}
	}

	close(done)

	time.Sleep(100 * time.Millisecond)
	fmt.Println("number of goroutine:", runtime.NumGoroutine())

	for _ = range nums {
	}

	time.Sleep(100 * time.Millisecond)
	fmt.Println("number of goroutine:", runtime.NumGoroutine())	
}
