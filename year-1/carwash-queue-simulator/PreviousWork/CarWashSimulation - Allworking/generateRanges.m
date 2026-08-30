function ranges = generateRanges(probabilities)
    % Generate predefined ranges based on probabilities
    cumulative_prob = cumsum(probabilities);
    ranges = cell(1, length(probabilities));
    lower_bound = 1;
    
    for i = 1:length(probabilities)
        upper_bound = round(cumulative_prob(i) * 100);
        ranges{i} = sprintf('%d - %d', lower_bound, upper_bound);
        lower_bound = upper_bound + 1;
    end
end
