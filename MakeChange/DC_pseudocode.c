functionmc (Amount)

k=Amount
if (i==one of our denominations){
    incriment array at correct denomination
    return
}else{
    for i=1;i<k
        val1=functionmc(i);//low values
        val2=functionmc(k-i);//high values
        update array with current min, compare to previous
        return sum=val1+val2;//low+high=totalAmount
}
