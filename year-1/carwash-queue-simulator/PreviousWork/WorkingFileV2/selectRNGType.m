function rng_type = selectRNGType()
    fprintf('Choose type of random number generator:\n');
    fprintf('1 - Linear Congruential Generator (LCG)\n');
    fprintf('2 - Random Variate Generator for Uniform Distribution\n');
    rng_type = input('Choice: ');
    while rng_type ~= 1 && rng_type ~= 2
        fprintf('Choose between 1 and 2 only\n');
        rng_type = input('Choice: ');
    end
end
