package main

type CarElementVisitor interface {
	VisitWheel(wheel Wheel)
	VisitEngine(engine Engine)
	VisitBody(body Body)
	VisitCar(car Car)
}


