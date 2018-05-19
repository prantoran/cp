package main

import (
	"fmt"
	"sort"
)

type Point struct {
	Type, Val int
}

type Points []Point

func (p Points) Less(i, j int) bool {
	if p[i].Val == p[j].Val {
		return p[i].Type > p[j].Type
	}
	return p[i].Val < p[j].Val
}

func (p Points) Swap(i, j int) {
	p[i], p[j] = p[j], p[i]
}

func (p Points) Len() int {
	return len(p)
}

func Solution(A []int) int {
	points := Points{}

	for _, val := range A {
		points = append(points, Point{1, val})
	}
	sort.Sort(points)

	for _, p := range points {
		fmt.Println("p:", p)
	}
	return 0
}

func main() {
	fmt.Println("sol:", Solution([]int{50, 29}))
}
