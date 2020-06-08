package main

import (
	"fmt"
	"runtime"
	"time"

	"golang.org/x/net/context"
)

func PlusOne(ctx context.Context, in <-chan int) <-chan int {
	out := make(chan int)
	go func() {
		defer close(out)
		for num := range in {
			select {
			case out <- num + 1:
			case <-ctx.Done():
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

	ctx, cancel := context.WithCancel(context.Background())
	nums := PlusOne(ctx, PlusOne(ctx, PlusOne(ctx, PlusOne(ctx, PlusOne(ctx, c)))))

	for num := range nums {
		fmt.Println("num:", num)
		if num == 18 {
			cancel()
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
