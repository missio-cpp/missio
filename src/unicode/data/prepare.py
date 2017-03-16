#!/usr/bin/env python
# -*- coding: utf-8 -*-

import urllib, urlparse

# -----------------------------------------------------------------------------

# URL for latest Unicode database root folder
URL_UNICODE_DATABASE            = 'http://www.unicode.org/Public/UCD/latest/ucd/'

# Unicode data files
IN_FILE_UNICODE_DATA            = 'UnicodeData.txt'
IN_FILE_CASE_FOLDING            = 'CaseFolding.txt'
IN_FILE_SPECIAL_CASING          = 'SpecialCasing.txt'
IN_FILE_COMPOSITION_EXCLUSIONS  = 'CompositionExclusions.txt'

# Result data files
OUT_FILE_CASE_FOLDING           = '../src/case_folding.inc'

# Unicode test files
FILE_NORMALIZATION_TEST         = 'NormalizationTest.txt'

# -----------------------------------------------------------------------------

def readDataFile( filename ):
  with open( filename, 'r' ) as file:
      for line in file:
          line = line.strip()

          if not bool( line ):
              continue

          if line.startswith( '#' ):
              continue

          entry, comment = [ x.strip() for x in line.split( '#', 1 ) ]

          yield entry, comment

# -----------------------------------------------------------------------------

def downloadFile( base_url, filename ):
    print 'Downloading data file: %s' % filename
    file_url = urlparse.urljoin( base_url, filename )
    return urllib.urlretrieve( file_url, filename )

# -----------------------------------------------------------------------------

def prepareUnicodeData():
    downloadFile( URL_UNICODE_DATABASE, IN_FILE_UNICODE_DATA )

# -----------------------------------------------------------------------------

def prepareSpecialCasing():
    downloadFile( URL_UNICODE_DATABASE, IN_FILE_SPECIAL_CASING )

# -----------------------------------------------------------------------------

def prepareCompositionExclusions():
    downloadFile( URL_UNICODE_DATABASE, IN_FILE_COMPOSITION_EXCLUSIONS )

# -----------------------------------------------------------------------------

def prepareCaseFolding():
    downloadFile( URL_UNICODE_DATABASE, IN_FILE_CASE_FOLDING )

    print 'Processing data file: %s' % IN_FILE_CASE_FOLDING

    with open( OUT_FILE_CASE_FOLDING, 'w' ) as file:
        for entry, comment in readDataFile( IN_FILE_CASE_FOLDING ):
            code, status, mapping = [ x.strip() for x in entry.split( ';' ) if bool( x ) ]

            if status == 'T':
                comment += ' - SPECIAL CASE FOR TURKIC LANGUAGES'

            mapping = str( ', ' ).join( [ '0x' + x for x in mapping.split() ] )

            file.write( '    { 0x%s, { %s } }, // %s\n' % ( code, mapping, comment ) )

# -----------------------------------------------------------------------------

prepareCaseFolding()
prepareUnicodeData()
prepareSpecialCasing()
prepareCompositionExclusions()

downloadFile( URL_UNICODE_DATABASE, FILE_NORMALIZATION_TEST )
