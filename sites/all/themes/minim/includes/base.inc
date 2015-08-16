<?php
/**
 * Preprocess and Helper Functions for core
 **/

/**
 * Implements hook_preprocess_hook
 */
function minim_preprocess_html(&$variables) {
  // Suggest seperate header and footer script variables in addition to scripts if needed.
  $variables['header_scripts'] = drupal_get_js('header');
  $variables['footer_scripts'] = drupal_get_js('footer');

  // Add css fonts to head
  $css_options = array('type' => 'external', 'group' => CSS_THEME);
  drupal_add_css('ttp://fonts.googleapis.com/css?family=Lato:400,900,700,300', $css_options);

}

function minim_preprocess_page(&$variables) {
  global $base_path;
  $variables['arrow_down'] = $base_path . drupal_get_path('theme', 'minim') . '/images/icon-arrow-down.png';
}

function minim_preprocess_node(&$v) {
  $function = __FUNCTION__ . '__' . $v['node']->type;
  if (function_exists($function)) {
    $function($v);
  }
}

function minim_preprocess_node__page(&$v) {

  $v['body'] = drupal_render($v['content']['body']);

}

function minim_preprocess_node__project(&$v) {
  $node = $v['node'];
  $l = $node->language;
  // Pick Layout
  if (!empty($node->field_layout[$l])) {
    switch($node->field_layout[$l][0]['tid']) {
      case 4:
        $v['theme_hook_suggestions'][] =  'node__project_layout_one';
        break;
      case 5:
        $v['theme_hook_suggestions'][] =  'node__project_layout_two';
        break;
      case 6:
        $v['theme_hook_suggestions'][] =  'node__project_layout_three';
        break;
    }
  }
  // Provide assets
  $v['body'] = drupal_render($v['content']['body']);
  if (!empty($node->field_project_date[$l])) {
    $date = $node->field_project_date[$l][0]['value'];
    $date = date('F jS, Y', strtotime($date)); 
    $v['date'] = $date;
  }
  if (!empty($node->field_project_tags[$l])) {
    $tags = array();
    foreach ($node->field_project_tags[$l] AS $field) {
      $term = taxonomy_term_load($field['tid']);
      $tags[] = l($term->name, 'projects', array('query' => array('field_project_tags_tid' => $term->tid)));
    }
    $v['tags'] = implode(', ', $tags);
  }
  if (!empty($node->field_additional_images[$l])) {
    $v['images'] = array();
    foreach ($node->field_additional_images[$l] AS $field) {
      $v['images'][] = theme('image', array('path' => $field['uri']));
    }
  }
  if (!empty($node->field_video[$l])) {
    $v['video'] = $node->field_video[$l][0]['value'];
  }
}
