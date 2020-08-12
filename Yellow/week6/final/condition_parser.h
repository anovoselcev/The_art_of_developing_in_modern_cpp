#pragma once

#include "node.h"

#include <memory>
#include <iostream>

using namespace std;

Date ParseDate(istream& is);

shared_ptr<Node> ParseCondition(istream& is);

void TestParseCondition();



