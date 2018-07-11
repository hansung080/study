package main

import (
	"fmt"
	"runtime"
	"time"
)

func PlusOne(in <-chan int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for num := range in {
			out <- num + 1	
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

	nums := PlusOne(PlusOne(PlusOne(PlusOne(PlusOne(c)))))

	for num := range nums {
		fmt.Println("num:", num)
		if num == 18 {
			break
		}
	}

	time.Sleep(100 * time.Millisecond)
	fmt.Println("number of goroutine:", runtime.NumGoroutine())

	for _ = range nums {
	}

	time.Sleep(100 * time.Millisecond)
	fmt.Println("number of goroutine:", runtime.NumGoroutine())	
}
