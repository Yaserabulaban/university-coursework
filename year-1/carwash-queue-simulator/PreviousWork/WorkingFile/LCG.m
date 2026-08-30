function rn = LCG(n, seed)
    % Linear Congruential Generator
    a = 1664525;
    c = 1013904223;
    m = 2^32;
    rn = zeros(1, n);
    rn(1) = seed;
    for i = 2:n
        rn(i) = mod(a * rn(i-1) + c, m);
    end
    rn = rn / m; % Normalize to [0, 1]
end