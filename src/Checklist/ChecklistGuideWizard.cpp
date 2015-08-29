#include "ChecklistGuidePage.h"
#include "ChecklistGuidePageConclusion.h"
#include "ChecklistGuidePageCurves.h"
#include "ChecklistGuidePageIntro.h"
#include "ChecklistGuideWizard.h"
#include "Logger.h"
#include "MainWindow.h"
#include <QGridLayout>
#include <QHeaderView>
#include <QPushButton>
#include <QRadioButton>
#include <QTextStream>
#include <QVBoxLayout>

const QString TAG_AXIS_1 ("[AXIS1]");
const QString TAG_AXIS_2 ("[AXIS2]");
const QString TAG_AXIS_3 ("[AXIS3]");
const QString TAG_EXPORT ("[EXPORT]");
const QString TAG_END ("]");
const QString TAG_START ("[");

ChecklistGuideWizard::ChecklistGuideWizard (MainWindow &mainWindow) :
  m_mainWindow (mainWindow),
  m_dialogName ("ChecklistGuide")
{
  setWindowTitle (tr ("Checklist Guide Wizard"));
  setModal (true);
  QPixmap splash (":/engauge/img/SpreadsheetsForDoc.png");
  setPixmap (QWizard::WatermarkPixmap, splash); // For ClassicStyle and ModernStyle
  setPixmap (QWizard::BackgroundPixmap, splash); // For MacStyle

  m_pageIntro = new ChecklistGuidePageIntro();
  m_pageCurves = new ChecklistGuidePageCurves();
  m_pageConclusion = new ChecklistGuidePageConclusion();

  addPage(m_pageIntro);
  addPage(m_pageCurves);
  addPage(m_pageConclusion);
}

QStringList ChecklistGuideWizard::curveNames() const
{
  return m_pageCurves->curveNames();
}

QString ChecklistGuideWizard::html () const
{
  QStringList curveNames = m_pageCurves->curveNames();
  bool withLines = m_pageCurves->withLines();

  QString html;
  QTextStream str (&html);

  str << "<p>The coordinates are first defined by creating three axis points:</p>\n";
  str << "<p>" << TAG_AXIS_1 << "&nbsp;Add first of three axis points.</p>\n";
  str << "<ul>\n";
  str << "<li>Click on <img src="":/engauge/img/12-DigitAxis""> for <b>Axis Points</b> mode</li>\n";
  str << "<li>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates</li>\n";
  str << "<li>Enter the coordinates of the axis point</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "</ul>\n";
  str << "<p>" << TAG_AXIS_2 << "&nbsp;Add second of three axis points.</p>\n";
  str << "<ul>\n";
  str << "<li>Click on <img src="":/engauge/img/12-DigitAxis""> for <b>Axis Points</b> mode</li>\n";
  str << "<li>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates, away from the other axis point</li>\n";
  str << "<li>Enter the coordinates of the axis point</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "</ul>\n";
  str << "<p>" << TAG_AXIS_3 << "&nbsp;Add third of three axis points.</p>\n";
  str << "<ul>\n";
  str << "<li>Click on <img src="":/engauge/img/12-DigitAxis""> for <b>Axis Points</b> mode</li>\n";
  str << "<li>Click on an axis tick mark, or intersection of two grid lines, with labeled coordinates, away from the other axis points</li>\n";
  str << "<li>Enter the coordinates of the axis point</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "</ul>\n";

  str << "<p>Points are digitized along each curve:</p>\n";
  QStringList::const_iterator itr;
  for (itr = curveNames.begin(); itr != curveNames.end(); itr++) {

    QString curveName = *itr;
    str << "<p>" << TAG_START << curveName << TAG_END << "&nbsp;Add points for curve <b>" << curveName << "</b></p>\n";
    str << "<ul>\n";

    if (withLines) {

      str << "<li>Click on <img src="":/engauge/img/12-DigitSegment""> for <b>Segment Fill</b> mode</li>\n";
      str << "<li>Select curve <b>" << curveName << "</b> in the drop-down list</li>\n";
      str << "<li>Move the cursor over the curve. If a line does not appear then adjust the <b>Color Filter</b> settings for this curve:\n";
      str << htmlToAdjustColorFilterSettings () << "</li>\n";
      str << "<li>Move the cursor over the curve again. When the <b>Segment Fill</b> line appears, click on it to generate points</li>\n";
      str << "</ul>\n";

    } else {

      str << "<li>Click on <img src="":/engauge/img/12-DigitPointMatch""> for <b>Point Match</b> mode</li>\n";
      str << "<li>Select curve <b>" << curveName << "</b> in the drop-down list</li>\n";
      str << "<li>Move the cursor over a typical point in the curve. If the cursor circle does not change color then adjust";
      str << "    the <b>Color Filter</b> settings for this curve:\n";
      str << htmlToAdjustColorFilterSettings () << "</li>\n";
      str << "<li>Move the cursor over a typical point in the curve again. Click on the point to start point matching</li>\n";
      str << "<li>Engauge will display a candidate point. To accept that candidate point, press the right arrow key</li>\n";
      str << "<li>The previous step repeats until you select a different mode</li>\n";
      str << "</ul>\n";
    }
  }

  str << "<p>" << TAG_EXPORT << "&nbsp;Export the points to a file</p>\n";
  str << "<ul>\n";
  str << "<li>Select menu option File / Export</li>\n";
  str << "<li>Enter the file name</li>\n";
  str << "<li>Click on Ok</li>\n";
  str << "<li>Congratulations!</li>\n";
  str << "</ul>\n";

  return html;
}

QString ChecklistGuideWizard::htmlToAdjustColorFilterSettings () const
{
  QString html;
  QTextStream str (&html);

  str << "  <ul>\n";
  str << "  <li>Select menu option Settings / Color Filter<li>\n";
  str << "  <li>Select the method for filtering. Hue is best if the curves have different colors</li>\n";
  str << "  <li>Slide the green buttons back and forth until the curve is easily visible in the preview window</li>\n";
  str << "  <li>Click on Ok</li>\n";
  str << "  </ul>\n";

  return html;
}