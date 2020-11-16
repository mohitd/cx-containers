// Copyright (c) 2020. Mohit Deshpande.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to permit
// persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE
// WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
// COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR
// OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#include <gtest/gtest.h>

#include "cx/cx_map.h"

static constexpr double kEpsilon = 1e-6;

enum class Lepton {
    kElectron,
    kMuon,
    kTau,
    kElectronNeutrino,
    kMuonNeutrino,
    kTauNeutrino,
};

TEST(Constructors, EmptyMap) {
    constexpr cx::map<Lepton, const char*, 0> lepton_name = {};
    static_assert(lepton_name.empty(), "");
}

TEST(Constructors, InitializerList) {
    constexpr cx::map<Lepton, const char*, 6> lepton_name = {
            {Lepton::kElectron, "electron"},
            {Lepton::kMuon, "muon"},
            {Lepton::kTau, "tau"},
            {Lepton::kElectronNeutrino, "electron neutrino"},
            {Lepton::kMuonNeutrino, "muon neutrino"},
            {Lepton::kTauNeutrino, "tau neutrino"},
    };
    static_assert(lepton_name.size() == 6, "");
}

TEST(ElementAccess, ValidLookup) {
    constexpr cx::map<Lepton, double, 6> lepton_masses = {
            {Lepton::kElectron, 0.511},
            {Lepton::kMuon, 105.66},
            {Lepton::kTau, 1776.},
            {Lepton::kElectronNeutrino, 1e-6},
            {Lepton::kMuonNeutrino, 0.17},
            {Lepton::kTauNeutrino, 18.2},
    };
    static_assert(lepton_masses.size() == 6, "");
    constexpr auto x = lepton_masses.at(Lepton::kElectronNeutrino);
    static_assert(std::abs(x - 1e-6) < kEpsilon, "");
}

TEST(ElementAccess, InvalidLookup) {
    constexpr cx::map<Lepton, const char*, 3> lepton_name = {
            {Lepton::kElectron, "electron"},
            {Lepton::kMuon, "muon"},
            {Lepton::kTau, "tau"},
    };
    //constexpr auto x = lepton_name.at(Lepton::kTauNeutrino);
}

TEST(Lookup, EmptyCount) {
    constexpr cx::map<int, double, 0> m = {};
    constexpr auto c = m.count(0);
    static_assert(c == 0, "");
}

TEST(Lookup, OneElement) {
    constexpr cx::map<int, double, 1> m = {
            {3, 3.14}
    };
    constexpr auto c = m.count(3);
    static_assert(c == 1, "");
}

TEST(Lookup, TwoElements) {
    constexpr cx::map<int, double, 2> m = {
            {3, 3.14},
            {3, 2.72}
    };
    constexpr auto c = m.count(3);
    static_assert(c == 2, "");
}

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
