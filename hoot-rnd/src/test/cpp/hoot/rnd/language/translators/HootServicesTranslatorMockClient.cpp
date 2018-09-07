/*
 * This file is part of Hootenanny.
 *
 * Hootenanny is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 * --------------------------------------------------------------------
 *
 * The following copyright notices are generated automatically. If you
 * have a new notice to add, please use the format:
 * " * @copyright Copyright ..."
 * This will properly maintain the copyright information. DigitalGlobe
 * copyrights will be updated automatically.
 *
 * @copyright Copyright (C) 2018 DigitalGlobe (http://www.digitalglobe.com/)
 */

#include "HootServicesTranslatorMockClient.h"

// hoot
#include <hoot/core/util/HootException.h>
#include <hoot/core/util/Log.h>
#include <hoot/core/util/ConfigOptions.h>
#include <hoot/core/util/Factory.h>

namespace hoot
{

HOOT_FACTORY_REGISTER(ToEnglishTranslator, HootServicesTranslatorMockClient)

HootServicesTranslatorMockClient::HootServicesTranslatorMockClient() :
HootServicesTranslatorClient()
{
  _mockTranslations[QString::fromUtf8("wie alt bist du")] =
    QString::fromUtf8("how old are you;German");
  _mockTranslations[QString::fromUtf8("wie heissen sie")] =
    QString::fromUtf8("what's your name;German");
  _mockTranslations[QString::fromUtf8("buenos noches")] =
    QString::fromUtf8("good night;Spanish");
  _mockTranslations[QString::fromUtf8("buenos dias")] =
    QString::fromUtf8("good morning;Spanish");
  _mockTranslations[QString::fromUtf8("computer store")] =
    QString::fromUtf8("computer store;English");
}

void HootServicesTranslatorMockClient::setSourceLanguages(const QStringList langCodes)
{
  LOG_DEBUG("Setting source languages...");
  _sourceLangs = langCodes;
}

void HootServicesTranslatorMockClient::translate(const QString textToTranslate)
{
  LOG_VART(textToTranslate);
  if (_sourceLangs.size() == 0)
  {
    throw HootException("Cannot determine source language.");
  }
  if (!_mockTranslations.contains(textToTranslate.normalized(QString::NormalizationForm_D)))
  {
    throw HootException("No mock translation available.");
  }

  LOG_DEBUG(
    "Translating to English with specified source languages: " <<
     _sourceLangs.join(",") << "; text: " << textToTranslate);

  _translatedText = _mockTranslations[textToTranslate].split(";")[0];
  _detectedLang = _mockTranslations[textToTranslate].split(";")[1];
  _detectionMade = true;
  _detectorUsed = "TikaLanguageDetector";
  _detectedLangAvailableForTranslation = true;

  emit translationComplete();
}

}
