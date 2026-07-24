function factorial(n)
    if (n < 0) then return nil end
    if (n < 2) then return n   end
    return n * factorial(n-1)
end
