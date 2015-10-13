% Test token parser

% Preconditions

%% Test 1: If empty cell is given an empty struct is returned
parsedS =parseToken({});
assert(isempty(fieldnames(parsedS)));
%% Test 2: If formated cell is given struct is returned
parsedS =parseToken({{'ax','1'}});
assert(isequal(parsedS,struct('ax',1)));
parsedS =parseToken({{'ay','2.5'}});
assert(isequal(parsedS,struct('ay',2.5)));
%% Test 2: If Well formated cell array is given struct with several fields is returned
parsedS =parseToken({{'ax','1'},{'ay','-2.5'}});
assert(isequal(parsedS,struct('ax',1,'ay',-2.5)));