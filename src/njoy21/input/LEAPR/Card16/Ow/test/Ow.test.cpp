#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "njoy21.hpp"

using namespace njoy::njoy21::input;

SCENARIO( "LEAPR Card16 ow input values",
  "[LEAPR], [Card16], [Ow]" ){
  GIVEN( "a small value for nd" ){
    Argument< LEAPR::Card14::Nd > nd;
    nd.value = 3;

    WHEN( "there are the correct number of ows and they are valid" ){
      iRecordStream< char> iss( std::istringstream(" 1.0 2.0 3.0") );

      THEN( "the ow values can be extracted correctly" ){
        auto ows = argument::extract< 
          LEAPR::Card16::Ow >(iss, nd);
          std::vector< double > refOws{ 1.0, 2.0, 3.0 };
        REQUIRE( refOws == ows.value );
      } // THEN
    } // WHEN
    WHEN( "the ow values are invalid" ){
      iRecordStream< char> iss( std::istringstream("-1.0 2.0 3.0") );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( argument::extract< 
          LEAPR::Card16::Ow >( iss, nd ) );
      } // THEN
    } // WHEN
    WHEN( "too few ow values are provided" ){
      iRecordStream< char> iss( std::istringstream("1.0 2.0") );
      THEN( "an exception is thrown" ){
        REQUIRE_THROWS( argument::extract<
          LEAPR::Card16::Ow >( iss, nd ) );
      } // THEN
    } // WHEN
    WHEN( "too many ow values are provided" ){
      iRecordStream< char> iss( std::istringstream("1.0 2.0 3.0 4.0") );
      THEN( "an exception is thrown" ){
        REQUIRE_NOTHROW( argument::extract<
          LEAPR::Card16::Ow >( iss, nd ) );
      } // THEN
    } // WHEN
  } // GIVEN

  GIVEN( "a larger value for nd" ){
    Argument< LEAPR::Card14::Nd > nd;
    nd.value = 7;

    WHEN( "there are the correct number of ows and they are valid" ){
      iRecordStream< char> iss( std::istringstream(
      ".010 .015 .025 .035\n"
      "2.5e-1 3.3e-1  5.04e-1/"
      ) );

      THEN( "the ow values can be extracted correctly" ){
        auto ows = argument::extract< 
          LEAPR::Card16::Ow >(iss, nd);
        std::vector< double > refOws{ .01, .015, .025, .035, .25, .33, .504 };
        REQUIRE( refOws == ows.value );
      } // THEN
    } // WHEN
  } // GIVEN
} // SCENARIO
