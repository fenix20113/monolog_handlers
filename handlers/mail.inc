<?php

use Drupal\Monolog\Handler\MailHandler;

/**
 * Monolog loader callback; Loads a MailHandler class.
 *
 * @return HandlerInterface
 */
function monolog_mail_handler_loader($options) {
  if ('<site-mail>' == $options['to']) {
    $options['to'] = variable_get('site_mail', ini_get('sendmail_from'));
  }
  if ('<site-mail>' == $options['from']) {
    $options['from'] = variable_get('site_mail', ini_get('sendmail_from'));
  }
  composer_manager_register_autoloader();

  if (!class_exists('Drupal\Monolog\Handler\MailHandler')) {
    $message = t('The Drupal\Monolog\Handler\MailHandler class was not found. Make sure the Monolog package is installed via Composer.');
    throw new \RuntimeException($message);
  }

  return new MailHandler($options['to'], $options['from'], $options['subject'], $options['level'], $options['bubble']);
}


/**
 * Monolog settings callback; Settings for the mail handler.
 */
function monolog_mail_handler_settings(&$form, &$form_state, $profile, array $handler) {

  $form['to'] = array(
    '#title' => t('Receiver'),
    '#type' => 'textfield',
    '#default_value' => $handler['to'],
    '#description' => t('The email address that messages will be sent to.<br/><code>&lt;site-mail&gt;</code> will use address that this site uses to send automated emails.'),
    '#required' => TRUE,
  );

  $form['subject'] = array(
    '#title' => t('Subject'),
    '#type' => 'textfield',
    '#default_value' => $handler['subject'],
    '#description' => t('The subject of the email address.'),
    '#required' => TRUE,
  );

  $form['from'] = array(
    '#title' => t('Sender'),
    '#type' => 'textfield',
    '#default_value' => $handler['from'],
    '#description' => t('The email address of the sender.<br/><code>&lt;site-mail&gt;</code> will use address that this site uses to send automated emails.'),
    '#required' => TRUE,
  );
}