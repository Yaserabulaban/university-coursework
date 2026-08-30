function ranges = generateRanges(probabilities)
    % Generate predefined ranges based on probabilities
    cumulative_prob = cumsum(probabilities);
    ranges = cell(1, length(probabilities));
    lower_bound = 1;
    
    for i = 1:length(probabilities)
        if probabilities(i) > 0
            upper_bound = round(cumulative_prob(i) * 100);
            if lower_bound > upper_bound
                upper_bound = lower_bound; % Ensure upper bound is not less than lower bound
            end
            ranges{i} = sprintf('%d - %d', lower_bound, upper_bound);
            lower_bound = upper_bound + 1;
        else
            ranges{i} = 'N/A';  % For probabilities that are zero, assign 'N/A'
        end
    end
end
