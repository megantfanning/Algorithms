Module Module1

    ' Globals 
    Dim iInputArray() As Integer = {3, 2, 1, 1, -8, 1, 1, 2, 3}
    Dim lStartTime As Long
    Dim lEndTime As Long
    Dim lDelta As Long

    Sub Main()

        BadEnum()
        BetterEnum()
        Console.ReadKey()

    End Sub

    ' Better enum 
    Private Sub BadEnum()

        ' Summation holding the latest max sum 
        Dim iMaxSum As Integer = iInputArray(0)

        ' Summation holding the current sum 
        Dim iCurSum As Integer = 0

        ' Holders for start and end max subarrays 
        Dim iStart, iEnd As Integer
        iStart = iEnd = 0

        ' Start the clocks 
        lStartTime = Now.Ticks

        ' Loop over the start index with nested loop for 
        ' end index 
        For i As Integer = 0 To iInputArray.Length - 1

            ' Init the iCurSum to the first value 
            iCurSum = iInputArray(i)

            For j As Integer = i + 1 To iInputArray.Length - 1

                ' Init current sum 
                iCurSum = iInputArray(i)

                ' Loop to get the sum from i to j 
                For k As Integer = i + 1 To j
                    iCurSum = iCurSum + iInputArray(k)
                Next

                ' Check to se if the current is bigger than max 
                ' and set the max and the start and end 
                If iCurSum > iMaxSum Then
                    iMaxSum = iCurSum
                    iStart = i
                    iEnd = j
                End If

            Next

        Next

        ' Get the end time 
        lEndTime = Now.Ticks
        lDelta = lEndTime - lStartTime

        ' Post the results 
        Console.WriteLine("Bad Algorithm " +
                          " Start:  " + iStart.ToString() +
                          " End: " + iEnd.ToString() +
                          " Sum: " + iMaxSum.ToString() +
                          " Delta: " + lDelta.ToString())
    End Sub

    ' Better enum 
    Private Sub BetterEnum()

        ' Summation holding the current sum
        Dim iCurSum As Integer

        ' Summation holding the latest max sum 
        Dim iMaxSum As Integer = iInputArray(0)

        ' Holders for start and end max subarrays 
        Dim iStart, iEnd As Integer
        iStart = iEnd = 0

        ' Start the clocks 
        lStartTime = Now.Ticks

        ' Loop over the start index with nested loop for 
        ' end index 
        For i As Integer = 0 To iInputArray.Length - 1

            ' Init the current sum with the first element 
            ' of the new starting value, i 
            iCurSum = iInputArray(i)

            For j As Integer = i + 1 To iInputArray.Length - 1

                ' Add on the next element 
                iCurSum = iCurSum + iInputArray(j)

                ' Check to se if the current is bigger than max 
                ' and set the max and the start and end 
                If iCurSum > iMaxSum Then
                    iMaxSum = iCurSum
                    iStart = i
                    iEnd = j
                End If

            Next

        Next

        ' Get the end time 
        lEndTime = Now.Ticks
        lDelta = lEndTime - lStartTime

        ' Post the results 
        Console.WriteLine("Good Algorithm " +
                          " Start: " + iStart.ToString() +
                          " End: " + iEnd.ToString() +
                          " Sum: " + iMaxSum.ToString() +
                          " Delta: " + lDelta.ToString())
    End Sub

End Module
	

// Enum pseudocode
MSS-ENUM (A)
      n = A.length
      max-sum = A[0]
      current-sum = 0
      start = 0
      end = 0
      for i = 0 to n - 1
            current-sum = A[i]
            for j = i + 1 to n - 1
                  current-sum = A[i]
                  for k = i + 1 to j
                        current-sum = current-sum + A[k]
                  if current-sum > max-sum
                        max-sum = current-sum
                        start = i
                        end = j
return (start, end, max-sum)

// Better Enum pseudocode
n = A.length
max-sum = A[0]
current-sum = 0
start = 0
end = 0
for i = 0 to n - 1
      current-sum = A[i]
      for j = i + 1 to n - 1
            current-sum = current-sum + A[j]
            if current-sum > max-sum
                  max-sum = current-sum
                  start = i
                  end = j
return (start, end, max-sum)


// DVC 
1) Find the answer of first half
2) Find the answer of the second half
3) Find the spanning max 
4) Find the max of those three 
? - whats the base case
	the base case is when the array is of length 1, so the max subarray is the array itself

// these are "adpated" (taken almost literally identically) from CLRS Ch 2
MSS-DAC-CROSS(A, low, mid, high)
      left-sum = -∞
      sum = 0
      for i = mid downto low
            sum = sum + A[i]
      if sum > left-sum
            left-sum =sum
            max-left = i
      right-sum = -∞
      sum = 0
      for j = mid + 1 to high
            sum = sum + A[j]
            if sum > right-sum
                  right-sum = sum
                  max-right = j
      return (max-left, max-right, left-sum + right-sum)
      
MSS-DAC (A, low, high)
      if high == low
            return (low, high, A[low])
      else
            mid = floor((low + high) / 2)
            (llow, lhigh, lsum) = MSS-DAC(A, low, mid)
            (rlow, rhigh, rsum) = MSS-DAC(A, mid + 1, high)
            (clow, chigh, csum) = MSS-DAC-CROSS(A, low, mid, high)
            if lsum >= rsum and lsum >= csum
                  return (llow, lhigh, lsum)
            elseif rsum >= lsum and rsum >= csum
                  return (rlow, rhigh, rsum)
            else return (clow, chigh, csum)


// Recursion inversion 
-- see 17 30 of the lecture
-- start at the smallest and work up to whole array 
// this is "adpated" (taken almost literally identically) from  the project1Alg4PC.pdf provided with the Project 1 materials
MSS-LINEAR (A)
      n = A.length
      max-sum = -∞
      ending-here-sum = -∞
      for j = 1 to n
            ending-here-high = j
            if ending-here-sum > 0
                  ending-here-sum = ending-here-sum + A[j]
            else
                  ending-here-low = j
                  ending-here-sum = A[j]
            if ending-here-sum > max-sum
                  max-sum = ending-here-sum
                  low = ending-here-low
                  high = ending-here-high
      return (low, high, max-sum)
